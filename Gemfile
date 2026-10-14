source "https://rubygems.org"

# Build locally with `bundle exec jekyll serve`. The site is deployed by
# .github/workflows/pages.yml, which builds with this same Gemfile.
gem "jekyll", "~> 4.4"

group :jekyll_plugins do
  gem "jekyll-optional-front-matter"
  gem "jekyll-relative-links"
  gem "jekyll-seo-tag"
  gem "jekyll-titles-from-headings"
end

# Ruby 3 no longer bundles webrick, which `jekyll serve` needs
gem "webrick", "~> 1.9"

# Windows and JRuby do not include zoneinfo files
platforms :windows, :jruby do
  gem "tzinfo", ">= 1", "< 3"
  gem "tzinfo-data"
end

# Performance-booster for watching directories on Windows
gem "wdm", "~> 0.2", platforms: [:windows]
